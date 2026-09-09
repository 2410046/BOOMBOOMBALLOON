#include "CSV.h"
#include <stdio.h>  //ファイル入出力で使用する.
#include <crtdbg.h> //ASSERT関数で使用する.
#include <string.h> //strtok_s関数で使用する.
#include <stdlib.h> //atoi関数で使用する.

CSV::CSV()
    : pInData   ( nullptr )
{
}

CSV::~CSV()
{
    pInData = nullptr;
}

//CSVファイルの読み込み(汎用性向上版).
bool CSV::LoadCSV(const char* fileName, ENEMY_DATA** pOutData, int& rowCount)
{
    FILE* pf;       // ファイルポインタ.
    errno_t error;  // エラー番号.

    // ファイルを開く.
    error = fopen_s(&pf, fileName, "r");    // r: 読み出し専用.
    if (error != 0)
    {
        _ASSERT_EXPR(false, L"CSVファイル読み込み失敗");
        return false;
    }

    // データの最大数分確保するためのメモリ（動的配列）
    ENEMY_DATA* pData = new ENEMY_DATA[DATA_MAX];

    char line[STR_MAX] = "";    // 1行単位で読み込む文字列格納用.
    char* pNext;                // 区切られた文字列へのポインタ.
    char delim[] = ",";         // デリミタ: 区切り文字.
    char* ctx = nullptr;        // 内部使用.

    int line_no = 0;

    // ファイルからデータを1行ずつ読み込む.
    while (fgets(line, STR_MAX, pf) != nullptr && line_no < DATA_MAX)
    {
        // 文字列から区切り文字までの文字列を取得
        pNext = strtok_s(line, delim, &ctx);
        int no = 0; // 〇番目の列

        // pNextが有効な間は繰り返し処理
        while (pNext)
        {
            // 〇番目ごとに取得したデータを格納
            switch (no)
            {
            case 0: pData[line_no].type = atoi(pNext); break;  // 音符のタイプ
            case 1: pData[line_no].time = atof(pNext); break;  // 出現時間
            case 2: pData[line_no].onkai = atoi(pNext); break; // 音階
            case 3: pData[line_no].Reset = atoi(pNext); break; // リセット
            }

            // 次の区切りまで文字列を取得
            pNext = strtok_s(nullptr, delim, &ctx);
            no++;  // 〇番目を進ませる
        }

        line_no++;  // 行数をインクリメント
    }

    // 行数を返す
    rowCount = line_no;

    // 出来上がったデータのポインタを出力用に渡す
    *pOutData = pData;

    // ファイル閉じる
    fclose(pf);

    return true;
}

//CSVデータの削除.
void CSV::DeleteCSV()
{
    //*pIdataの中身がnullptrでない=何かデータが入っているということ.
    if (pInData != nullptr)
    {
        //delete 演算子  :new 演算子で動的に確保したメモリを開放する.
        //delete[] 演算子:new 演算子で配列として動的に確保したメモリを開放する.
        delete[]  pInData;
        pInData = nullptr; //nullptrで初期化する.
    }
}
