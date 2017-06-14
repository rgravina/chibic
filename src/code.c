#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "code.h"
#include "node.h"

void write_file();

void cc_generate_code() {
  write_file();
}

void write_file() {
    FILE *out = fopen("out.s", "wb");
    fprintf(out, ".section __TEXT,__text\n");
    fprintf(out, "    .globl _main\n\n");
    fprintf(out, "_main:\n");
    fprintf(out, "    movl    $0x2000001, %%eax\n");
    fprintf(out, "    movl    $0, %%ebx\n");
    fprintf(out, "    syscall\n");
    fclose(out);
}
