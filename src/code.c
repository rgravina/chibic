#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "code.h"
#include "node.h"

void write_file();

void cc_generate_code(bool write_to_file) {
  if (write_to_file) {
    write_file();
  }
}

void write_file() {
    FILE *out = fopen("bin/out.s", "wb");
    fprintf(out, "        .section __TEXT,__text,regular,pure_instructions\n");
    fprintf(out, "        .macosx_version_min 10, 12\n");
    fprintf(out, "        .globl _main\n\n");
    fprintf(out, "_main:\n");
    fprintf(out, "        movl    $0x2000001, %%eax\n");
    fprintf(out, "        movl    $0, %%ebx\n");
    fprintf(out, "        syscall\n");
    fclose(out);
}
