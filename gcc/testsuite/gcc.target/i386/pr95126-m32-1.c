/* { dg-do compile { target { ia32 } } } */
/* { dg-options "-O2" } */

struct small{ short a,b; signed char c; };

void call_func(void)
{
    extern int func(struct small X);
    static struct small const s = { 1,2,0 };
    func(s);
}

/* { dg-final { scan-assembler "movl\[ \\t]*\\\$" } } */
/* { dg-final { scan-assembler "movb\[ \\t]*\\\$0, " } } */
/* { dg-final { scan-assembler-not "movzwl" } } */

