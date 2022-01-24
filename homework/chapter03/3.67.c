
// A.E.
// |       z       |
// |       x       |
// |       y       |+64
// |       .       |
// |       .       |
// |       .       |
// |       z       |
// |      &z       |
// |       y       |
// |       x       |+0 <- %rsp @ eval() line 8
// | ret eval addr |-8 <- %rsp @ process() line 2
//
// B. %rdi = 64(%rsp)
// C. &s => 8(%rsp)
// D. &r => %rdi
// E. y => 64(%rsp)
//    x => 72(%rsp)
//    z => 80(%rsp)
// F. all structs are stored on the caller stack, 
//    because the callee stack will release when function return.

