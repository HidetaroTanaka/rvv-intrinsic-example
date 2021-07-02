#include<stdio.h>
#include <riscv_vector.h>

int main(void) {
	vint32m8_t varray1, varray2, varray3;
	int array1[8] = {0,1,2,3,4,5,6,7};
	int array2[8] = {8,9,10,11,12,13,14,15};
	int array3[8] = {0,0,0,0,0,0,0,0};
	
	varray1 = vle32_v_i32m8(array1, 8);
	varray2 = vle32_v_i32m8(array2, 8);
	varray3 = vadd_vv_i32m8(varray1, varray2, 8);

	vse32_v_i32m8(array3, varray3, 8);
	int i;
	for(i=0; i<8; i++) {
		printf("%d\n", array3[i]);
	}
	return 0;
}

