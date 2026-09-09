#pragma once
/********************************************************************************
*	CSVクラス
**/
class CSV
{
public:
	CSV();
	~CSV();

    //定数宣言.C++での書き方.
    static const int DATA_MAX = 600;    //読み込むデータの行数.
    static const int STR_MAX = 256;    //1行の最大数(byte数).


    //CSVデータ構造体.
    struct ENEMY_DATA
    {
        int   type;                  // 音符のタイプ
        double time;                   // 出現時間
        int   onkai;      // 音階
        bool  Reset;
    };

    //CSVファイルの読み込み(汎用性向上版).
    bool LoadCSV(const char* fileName, ENEMY_DATA** pOutData, int& rowCount);

    //CSVデータの削除.
    void DeleteCSV();

private:
    //int** pInData;
    ENEMY_DATA* pInData;  // 動的に確保したデータのポインタ
};

