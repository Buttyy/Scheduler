# Scheduler
スケジューラの3つのアルゴリズム(到着順、処理時間順、ラウンドロビン)を同じタスクに同時に適用し、それぞれの応答時間を表示します。

## 使用方法
1. `main.c`，`scheduler.c`を1つのファイルにコンパイルしてください。<br>
  文字化けする場合は`-fexec-charset=CP932`を指定してください。<br>
  例: `gcc -o scheduler main.c scheduler.c -fexec-charset=CP932`
2. 実行してください。
3. ラウンドロビンの定時間を入力してください。
4. 処理するタスク数を100以下で入力してください。
5. タスクを生成する方法を選択してください。(1:指定 2:ランダム)
6. 「指定」を選択した場合は、2文字以下のタスクの名前、到着時刻、処理時間の順にそれぞれ入力してください。
7. 「ランダム」を選択した場合は、生成されたタスクが表示されます。
8. シミュレーション結果、タスクそれぞれの応答時間、アルゴリズムそれぞれの応答時間の平均、最小、最大が表示されます。

### 実行例
```
===== Scheduler =====
ラウンドロビンの定時間: 2
タスク数(100以下): 4

--- タスク生成 ---
1: 指定
2: ランダム
選択: 1
名前 | 到着時刻 | 処理時間
A 0 2
B 1 10
C 3 7
D 5 3

--- シミュレーション ---
START
時刻 |   到着順   | 処理時間順 | ラウンドロビン
   1 | Task:A     | Task:A     | Task:A
   2 | Task:A  fin| Task:A  fin| Task:A  fin
   3 | Task:B     | Task:B     | Task:B
   4 | Task:B     | Task:B     | Task:B
   5 | Task:B     | Task:B     | Task:C
   6 | Task:B     | Task:B     | Task:C
   7 | Task:B     | Task:B     | Task:B
   8 | Task:B     | Task:B     | Task:B
   9 | Task:B     | Task:B     | Task:D
  10 | Task:B     | Task:B     | Task:D
  11 | Task:B     | Task:B     | Task:C
  12 | Task:B  fin| Task:B  fin| Task:C
  13 | Task:C     | Task:D     | Task:B
  14 | Task:C     | Task:D     | Task:B
  15 | Task:C     | Task:D  fin| Task:D  fin
  16 | Task:C     | Task:C     | Task:C
  17 | Task:C     | Task:C     | Task:C
  18 | Task:C     | Task:C     | Task:B
  19 | Task:C  fin| Task:C     | Task:B
  20 | Task:D     | Task:C     | Task:C  fin
  21 | Task:D     | Task:C     | Task:B
  22 | Task:D  fin| Task:C  fin| Task:B  fin
END

--- 応答時間 ---
名前 |   到着順   | 処理時間順 | ラウンドロビン
  A  |          2 |          2 |          2
  B  |         11 |         11 |         21
  C  |         16 |         19 |         17
  D  |         17 |         10 |         10

--- 比較 ---
       |   到着順   | 処理時間順 | ラウンドロビン
平均値 |      11.50 |      10.50 |      12.50
最小値 |          2 |          2 |          2
最大値 |         17 |         19 |         21
```
