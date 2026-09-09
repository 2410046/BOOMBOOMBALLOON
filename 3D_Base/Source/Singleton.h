#pragma once
template<typename T>
class Singleton
{
public:
	/************************************************
	* @brief シングルトンのインスタンスを取得.
	* @return インスタンスのポインタ.
	************************************************/
	static T* GetInstance() {
		static T instance;
		return &instance;
	}
protected:
	// 継承先以外でのコンストラクタ、デストラクタの使用禁止.
	Singleton() {};
	virtual ~Singleton() {};
private:
	// 外部からアクセス不可.
	// 外部からコンストラクタへのアクセスを禁止する.
	Singleton(const Singleton& obj) = delete;

	// 代入演算子によるコピーを禁止する.
	// operator(演算子): 演算子のオーバーロードで、演算の中身を拡張できる.
	Singleton& operator = (const Singleton& obj) = delete;
};