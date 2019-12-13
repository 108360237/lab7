#include <stdio.h>
#include <stdlib.h>

struct clientData {
	int acctNum;
	char lName[15];
	char fName[10];
	double balance;
};

void main()
{
	FILE *pR, *pW, *cfPtr;
	int cnt = 0;
	struct clientData client = { 0,"","",0.0 };
	fopen_s(&pR, "c://credit.txt", "r");
	if (pR == NULL)
	{
		return;
	}
	fopen_s(&pW, "c://credit_bin.txt", "wb");
	if (pW == NULL)
	{
		fclose(pR);
		return;
	}

	while (!feof(pR))
	{
		fscanf_s(pR, "%d", &client.acctNum);
		fscanf_s(pR, "%s", client.lName, 15);
		fscanf_s(pR, "%s", client.fName, 10);
		fscanf_s(pR, "%f", &client.balance);
		fwrite(&client, sizeof(struct  clientData), 1, pW);
		printf("%-6d%-16s%-11s%10.2f\n", client.acctNum, client.lName, client.fName, client.balance);
	}
	fclose(pR);
	fclose(pW);
	printf("已讀取文字檔的ASCII資料，並轉存成二進位資料檔案\n\n");
	system("PAUSE");

	printf("\n讀取二進位資料檔案，並格式化輸出如下：\n");
	fopen_s(&cfPtr, "c://credit_bin.txt", "rb");
	if ((cfPtr) == NULL)
	{
		printf("File could not be opened.");
	}
	else
	{
		printf("%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");

		cnt = fread(&client, sizeof(struct clientData), 1, cfPtr);

		while (cnt > 0)
		{
			printf("%-6d%-16s%-11s%10.2f\n", client.acctNum, client.lName, client.fName, client.balance);
			cnt = fread(&client, sizeof(struct clientData), 1, cfPtr);
		}
		fclose(cfPtr);
	}
	system("PAUSE");
}