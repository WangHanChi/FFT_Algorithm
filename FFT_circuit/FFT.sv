`timescale 1ns/1ps

import complex_type::*;

module FFT #(
    parameter DATA_WIDTH = 32,
    parameter N = 8,
    parameter STAGE = 3
) (
    input logic clk, 
    input logic rst, 
    input logic vaild, 
    input Complex data_in [0:N-1],
    output Complex data_out [0:N-1],
    output logic ready
);


logic valid_ff1;
logic valid_ff2;
logic valid_ff3;
//定义旋转因子常量
Complex WN0 = '{65536,0};           
Complex WN1 = '{46340,-46340};
Complex WN2 = '{0,-65535};
Complex WN3 = '{-46340,-46341};
//中间结果
Complex tmp [0:STAGE][0:N-1];                                          //STAGE=log2(N),为蝶形运算单元的级数
//蝶形运算
//第1级 tmp[0]-->tmp[1]
always_ff@(posedge clk)                 //第一级,蝶形单元跨度为1=2^0
for(int i=0;i<N;i+=2)
begin
    tmp[1][i]<=complex_add(tmp[0][i],complex_mul(tmp[0][i+1],WN0));
    tmp[1][i+1]<=complex_sub(tmp[0][i],complex_mul(tmp[0][i+1],WN0));
    // $write("mult=%d,%d\n",complex_mul(tmp[0][1],WN0).r,complex_mul(tmp[0][1],WN0).i);
    // for(int j=0;j<2;j++)
    //     $write("i=%d,%d,%d\n",i+j,tmp[1][i+j].r>>>16,tmp[1][i+j].i>>>16);
end
//第2级 tmp[1]-->tmp[2]                 
always_ff@(posedge clk)
for(int i=0;i<N;i+=4)                   //第二级，蝶形单元跨度为2=2^1
begin
    tmp[2][i]<=complex_add(tmp[1][i],complex_mul(tmp[1][i+2],WN0));
    tmp[2][i+1]<=complex_add(tmp[1][i+1],complex_mul(tmp[1][i+3],WN2));
    tmp[2][i+2]<=complex_sub(tmp[1][i],complex_mul(tmp[1][i+2],WN0));
    tmp[2][i+3]<=complex_sub(tmp[1][i+1],complex_mul(tmp[1][i+3],WN2));
end
//第3级 tmp[2]-->tmp[3]
always_ff@(posedge clk)
for(int i=0;i<N;i+=8)                  //第三级，蝶形单元跨度为4=2^2                                            第i级span=2^(i-1)
begin
    tmp[3][i]<=complex_add(tmp[2][i],complex_mul(tmp[2][i+4],WN0));
    tmp[3][i+1]<=complex_add(tmp[2][i+1],complex_mul(tmp[2][i+5],WN1));
    tmp[3][i+2]<=complex_add(tmp[2][i+2],complex_mul(tmp[2][i+6],WN2));
    tmp[3][i+3]<=complex_add(tmp[2][i+3],complex_mul(tmp[2][i+7],WN3));
    tmp[3][i+4]<=complex_sub(tmp[2][i],complex_mul(tmp[2][i+4],WN0));
    tmp[3][i+5]<=complex_sub(tmp[2][i+1],complex_mul(tmp[2][i+5],WN1));
    tmp[3][i+6]<=complex_sub(tmp[2][i+2],complex_mul(tmp[2][i+6],WN2));
    tmp[3][i+7]<=complex_sub(tmp[2][i+3],complex_mul(tmp[2][i+7],WN3));
end
//data_out
always_comb 
begin
    for(int i=0;i<N;i++)
        data_out[i]=tmp[3][i];    
end
//data_in,bit reverse
always_ff@(posedge clk)
begin
    tmp[0][0]<=data_in[0];
    tmp[0][1]<=data_in[4];
    tmp[0][2]<=data_in[2];
    tmp[0][3]<=data_in[6];
    tmp[0][4]<=data_in[1];
    tmp[0][5]<=data_in[5];
    tmp[0][6]<=data_in[3];
    tmp[0][7]<=data_in[7];
end
//ready,延迟为4个周期，一个周期bit reverse,3个周期计算
always_ff@(posedge clk)
    {ready,valid_ff3,valid_ff2,valid_ff1}<={valid_ff3,valid_ff2,valid_ff1,valid};
endmodule