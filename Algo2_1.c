#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void MergeSort(int * arr, int lef, int rig);
void Merge(int * arr, int lef, int mid, int rig);

int main(void) {
	int *arr; // ������ �����͸� ������ ������ ���� ����.
	int size = 1;
	FILE* f; // ����
	int i = 0;
	int startTime = 0, endTime = 0;
	float gap;

	f = fopen("test_10000.txt", "r");

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
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
	
	printf("���� �ð� : %f ��\n", gap);

	free(arr);
	fclose(f);

	system("pause"); // �׽�Ʈ ���� ����.

}

void MergeSort(int * arr, int lef, int rig)
{
	int mid;

	if (lef < rig)
	{
		mid = (lef + rig) / 2; // ����Ʈ�� ������ ������.

		MergeSort(arr, lef, mid); // �κ� ����Ʈ ����(����)
		MergeSort(arr, mid + 1, rig); // �κ� ����Ʈ ����(������)
		Merge(arr, lef, mid, rig); // ��ġ��
	}
}

void Merge(int * arr, int lef, int mid, int rig)
{
	int i = lef; // ���� ����Ʈ�� ���� �ε���
	int j = mid + 1; // ������ ����Ʈ�� ���� �ε���
	int k = lef; // ����Ʈ�� ���� �ε���
	int l;
	int *sorted;

	sorted = (int*)malloc(sizeof(int)*(rig+1));

	/* ���� ���ĵ� ����Ʈ �պ�*/
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

	/*�迭 sorted[]�� ����Ʈ�� �迭 arr[]�� ����*/
	for (l = lef;l <= rig; l++)
		arr[l] = sorted[l];

}