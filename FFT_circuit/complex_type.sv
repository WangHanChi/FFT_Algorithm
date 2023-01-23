`timescale 1ns/1ps

package complex_type
    parameter DATA_WIDTH = 32;
    // Complex Struct
   typedef struct packed {
    logic signed [DATA_WIDTH-1:0] Re;
    logic signed [DATA_WIDTH-1:0] Im;
   } Complex;

   // Complex calculate funcnction

   // mul
   function Complex complex_mul(Complex a, Complex b);
    // (a.Re + i*a.Im) x (b.Re + i*b.Im)
    Complex result;
    // avoid overflow, we extend to 64 bits before mul
    logic [2*DATA_WIDTH-1 : 0 ] expand_a_Re;
    logic [2*DATA_WIDTH-1 : 0 ] expand_a_Im;
    logic [2*DATA_WIDTH-1 : 0 ] expand_b_Re;
    logic [2*DATA_WIDTH-1 : 0 ] expand_b_Im;
    // $display("a = (%d, %d), b = (%d, %d)". a.Re, a.Im, b.Re, b.Im);
    expand_a_Re={{32{a.Re[31]}}, a.Re};
    expand_a_Im={{32{a.Im[31]}}, a.Im};
    expand_b_Re={{32{b.Re[31]}}, b.Re};
    expand_b_Im={{32{b.Im[31]}}, b.Im};
    result.Re = (expand_a_Re * expand_b_Re - expand_a_Im * expand_b_Im) >>> 16;
    result.Im = (expand_a_Re * expand_b_Im + expand_a_Im * expand_b_Re) >>> 16;
    // $display("result = (%d, %d)". result.Re, result.Im);
    return result;
   endfunction

   function Complex compliex_add(Complex a, Complex b);
    Complex result;
    result.Re = a.Re + b.Re;
    Result.Im = a.Im + b.Im;
    return result;
   endfunction

   function Complex complex_sub(Complex a, Complex b);
    Complex result;
    result.Re = a.Re - b.Re;
    result.Im = a.Im - b.Im;
    return result;
   endfunction
endpackage