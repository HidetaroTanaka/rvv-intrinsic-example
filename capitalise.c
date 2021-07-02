#include<stdio.h>
#include<riscv_vector.h>

void capitalise(char* string) {
    char* ptr = string;
    while(*ptr != '\0') {
        if(*ptr >= 'a' && *ptr <= 'z') {
            *ptr -= 'a' - 'A';
        }
        ptr++;
    }
    return;
}

int main(void) {
    vint8m1_t string_reg;
    vbool8_t tmp_mask0;
    vbool8_t tmp_mask1;
    vbool8_t string_mask;
    char string[16] = "Hello, World!";
    string_reg = vle8_v_i8m1(string, 16);
    // 要素が'a'未満ならばマスクを0にリセット
    // 'a'以上ならば1をセット
    tmp_mask0 = vmsge_vx_i8m1_b8(string_reg, 'a', 16);
    // 要素が'z'より大きければマスクを0にリセット
    // 'z'以下ならば1をセット
    tmp_mask1 = vmsle_vx_i8m1_b8(string_reg, 'z', 16);
    // string_mask = tmp_mask0 && tmp_mask1
    // 'a' <= string_reg[i] <= 'z'
    string_mask = vmand_mm_b8(tmp_mask0, tmp_mask1, 16);
    string_reg = vsub_vx_i8m1(string_reg, 32, 16);
    vse8_v_i8m1_m(string_mask, string, string_reg, 16);
    printf("%s\n", string);
    return 0;
}