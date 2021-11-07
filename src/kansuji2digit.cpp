// Copyright (c) 2021 nanamedou

#include <string.h>
#include <iostream>
#include <tuple>
#include <iterator>

#include <iso646.h>

#include "kansuji2digit.h"

bytes c_num_digit[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
bytes c_num_kanji[] = {"〇", "一", "二", "三", "四", "五", "六", "七", "八", "九"};
const size_t num_size = std::size(c_num_kanji);
bytes c_num_digit_zero = c_num_digit[0];
bytes c_num_digit_one = c_num_digit[1];

const size_t u_zeros_log10[] = {4, 8, 12, 16, 20, 24, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68};
bytes c_zeros_kanji[] = {"万", "億", "兆", "京", "垓", "𥝱", "秭", "穣", "溝", "澗", "正", "載", "極", "恒河沙", "阿僧祇", "那由他", "不可思議", "無量大数"};
const size_t zeros_size = std::size(c_zeros_kanji);

const size_t u_zeros3_log10[] = {1, 2, 3};
bytes c_zeros3_kanji[] = {"十", "百", "千"};
const size_t zeros3_size = std::size(c_zeros3_kanji);

// 1~9の漢数字をアラビア文字に変換
std::tuple<str, size_t> kanji2digit(bytes &data)
{
	str out_str;		 // 戻り値の文字列
	size_t out_size = 0; // 戻り値の文字列の文字列としての長さ

	while (data[0])
	{
		bool is_unknown = true; // 先頭の文字列が不明である

		// 先頭の文字列が既知のものか比べる
		for (size_t i = 0; i < num_size; i++)
		{
			size_t c_size = strlen(c_num_kanji[i]);
			if (0 == strncmp(data, c_num_kanji[i], c_size))
			{
				// 先頭の文字列が判明したとき
				// 戻り値に文字を追加して、読み取りポインタを進める
				out_str += c_num_digit[i];
				data += c_size;
				out_size += 1;
				is_unknown = false;
				break;
			}
		}

		// 文字列が解決できなかったら終了
		if (is_unknown)
			break;
	}

	return {out_str, out_size};
}

// 0~9999の漢数字をアラビア文字に変換
// 文字, 文字列の桁数
std::tuple<str, size_t> kansuji9999_2digit(bytes &data)
{
	str out_str;		 // 戻り値の文字列
	size_t out_size = 0; // 戻り値の文字列の文字列としての長さ

	size_t zeros = 0; // 戻り値の文字列に追加する0の個数(out_str * (10^zeros) が実際の値になる)
	bool initial = true;

	while (data[0])
	{

		// 戻り値の文字列
		size_t add_zeros = 0; // 戻り値の文字列

		auto [num_str, u8cc] = kanji2digit(data); // 戻り値の文字列

		bool is_unknown = true; // 先頭の文字列が不明である

		// 先頭の文字列が既知のものか比べる
		for (size_t i = 0; i < zeros3_size; i++)
		{
			size_t c_size = strlen(c_zeros3_kanji[i]);
			if (0 == strncmp(data, c_zeros3_kanji[i], c_size))
			{
				// 先頭の文字列が判明したとき
				// 後に追加する0の数を取得
				add_zeros = u_zeros3_log10[i];
				data += c_size;
				is_unknown = false;

				// 頭に何も数字がないとき、例えば百とかのとき。1を追加する。
				if (0 == u8cc)
				{
					num_str += c_num_digit_one;
					u8cc += 1;
				}
				break;
			}
		}

		if (not initial)
		{
			// 二百千のような変な数値のときエラー
			if (zeros < (add_zeros + u8cc))
			{
				return {"NaN", -1};
			}

			// out_strに0を追加。1*(10^4)に11*(10^0)のような値を追加するとき4-(2+0) = 2個0を追加する。
			if (zeros > (add_zeros + u8cc))
				for (size_t i = 0; i < (zeros - (add_zeros + u8cc)); i++)
				{
					out_str += c_num_digit_zero;
					out_size += 1;
				}
		}
		initial = false;

		out_str += num_str; // 数字を追加。
		out_size += u8cc;	// 文字数を追加。
		zeros = add_zeros;	// 追加する0の個数は現在のものとなる

		// 文字列が解決できなかったら終了
		if (is_unknown)
			break;
	}

	// 末尾に追加の0を適用する
	for (size_t i = 0; i < zeros; i++)
		out_str += c_num_digit_zero;
	out_size += zeros;

	return {out_str, out_size};
}

str kansuji2digit(const str &s)
{
	bytes data = s.c_str();

	str out_str;
	size_t zeros = 0;
	size_t out_size = 0;
	bool initial = true;

	while (data[0])
	{
		size_t add_zeros = 0;

		auto [num_str, u8cc] = kansuji9999_2digit(data);

		if (-1 == u8cc)
			return "NaN"; // 戻り値がエラーの時NaNを返す

		bool is_unknown = true; // 先頭の文字列が不明である

		for (size_t i = 0; i < zeros_size; i++)
		{
			size_t c_size = strlen(c_zeros_kanji[i]);
			if (0 == strncmp(data, c_zeros_kanji[i], c_size))
			{
				add_zeros = u_zeros_log10[i];
				data += c_size;
				is_unknown = false;

				// 頭に何も数字がないとき、例えば百とかのとき。1を追加する。
				if (0 == u8cc)
				{
					num_str += c_num_digit_one;
					u8cc += 1;
				}
				break;
			}
		}

		if (not initial)
		{
			// 二万一億のような変な数値のときエラー
			if (zeros < (add_zeros + u8cc))
			{
				return "NaN";
			}

			// 数字を追加する
			if (zeros > (add_zeros + u8cc))
				for (size_t i = 0; i < (zeros - (add_zeros + u8cc)); i++)
					out_str += c_num_digit_zero;
		}
		initial = false;
		out_size += 1;
		out_str += num_str;
		out_size += u8cc;
		zeros = add_zeros;

		// 文字列が解決できなかったら終了
		if (is_unknown)
			break;
	}

	// 末尾に追加の0を適用する
	for (size_t i = 0; i < zeros; i++)
		out_str += c_num_digit_zero;

	return out_str;
}


char const* Kansuji2Digit::translate(char const* s){
	this->buffer = kansuji2digit(s);
	return this->buffer.c_str();
}
