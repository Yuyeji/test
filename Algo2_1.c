#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void MergeSort(int * arr, int lef, int rig);
void Merge(int * arr, int lef, int mid, int rig);

int main(void) {
	int *arr; // 파일의 데이터를 저장할 포인터 변수 선언.
	int size = 1;
	FILE* f; // 파일
	int i = 0;
	int startTime = 0, endTime = 0;
	float gap;

	f = fopen("test_10000.txt", "r");

	if (f == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}

	arr = (int *)malloc(sizeof(int));

	while (feof(f) == 0) {
		arr = (int *)realloc(arr, (size) * sizeof(int));
		fscanf(f, "%d", &arr[i]);
		size++;
		i++;
	}

	startTime = clock();

	MergeSort(arr, 0, size - 1);

	endTime = clock();

	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);
	
	
	for (int j = 0; j < size - 1; j++) {
		printf("%d\n", arr[j]);
	}
	
	printf("측정 시간 : %f 초\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // 테스트 보기 위해.

}

void MergeSort(int * arr, int lef, int rig)
{
	int mid;

	if (lef < rig)
	{
		mid = (lef + rig) / 2; // 리스트를 반으로 나눈다.

		MergeSort(arr, lef, mid); // 부분 리스트 정렬(왼쪽)
		MergeSort(arr, mid + 1, rig); // 부분 리스트 정렬(오른쪽)
		Merge(arr, lef, mid, rig); // 합치기
	}
}

void Merge(int * arr, int lef, int mid, int rig)
{
	int i = lef; // 왼쪽 리스트에 대한 인덱스
	int j = mid + 1; // 오른쪽 리스트에 대한 인덱스
	int k = lef; // 리스트에 대한 인덱스
	int l;
	int *sorted;

	sorted = (int*)malloc(sizeof(int)*(rig+1));

	/* 분할 정렬된 리스트 합병*/
	while (i <= mid && j <= rig) {
		if (arr[i] <= arr[j])
			sorted[k++] = arr[i++];
		else
			sorted[k++] = arr[j++];
	}

	if (i > mid)
		for (l = j; l <= rig; l++)
			sorted[k++] = arr[l];
	else
		for (l = i; l <= mid; l++)
			sorted[k++] = arr[l];

	/*배열 sorted[]의 리스트를 배열 arr[]로 복사*/
	for (l = lef;l <= rig; l++)
		arr[l] = sorted[l];

}