//2020111842 금명섭
#include <stdio.h>
#include <stdlib.h>
int findMax(int arr[], int size) {
	if (size == 1) {
		return arr[0]; //하나밖에 없을때
	}
	// 현재 요소와 나머지 요소들 중 최댓값을 비교하여 최댓값을 갱신
	int sub = findMax(arr + 1, size - 1);
	if (arr[0] > sub) {
		return arr[0]; //크면 바꿔주고
	}
	else {
		return sub; //작으면 그대로
	}
}

int main() {
	int num;
	FILE* fp;
	fopen_s(&fp,"in.txt", "r"); //파일 읽기
	fscanf_s(fp, "%d", &num);
	int* nums = (int*)malloc(num * sizeof(int)); //동적할당
	for (int i = 0; i < num; i++) {
		fscanf_s(fp, "%d", &nums[i]);
	}
	printf("숫자리스트>>\n");
	for (int i = 0; i < num; i++) {
		printf("%d ", nums[i]);
	}
	printf("\n최대값 : %d",findMax(nums, num));
	free(nums);
	fclose(fp);
	return 0;
}