# kansuji2digit

漢数字->アラビア数字変換

## ビルド方法(windows)

win_setup.batのvcvarsallのパスを通す
win_setup.batを実行
win_install.batを実行
実行ファイル(main.exe)とpython用ライブラリ(_kansuji2digit.pyd)が得られる。

## 実行例

入出力は基本的にutf-8

cmd

```cmd
> echo 九十八万八〇〇〇 | main.exe
98000
```

python

```python
>>import kansuji2digit
>>k2d = kansuji2digit.Converter()
>>print(k2d.kansuji2digit("九百二億三千百七万四千百三十八"))
90231074138
```
