# TODO

自動テスト機能
メモリアクセス命令
分岐

# 命令について

## 命令長
64bit長命令を採用。メモリアクセスも同じ

## 命令デザイン

0             14   17    22    27    32                               64
+--------------|--- |-----|-----|-----|--------------------------------|
|opecode       |func|dest |reg1 |reg2 |immedinate                      |

opecode: 14
func: 3
dest 5
reg1: 5
reg2: 5


## 命令一覧

- instruction name
  - opecode

0
+
|S


S: Sensitive 

### 算術
- ADD(dabi)
  - 0b0000_0000_0001_00
- SUB(dabi)
  - 0b0000_0000_0010_00
- MUL_ADD(dabi)
  - 0b0000_0000_0011_00
- DIV_ADD(dabi)
  - 0b0000_0000_0100_00

### メモリ
- LOAD(fdai)
  - 0b0000_0001_0000_00
- STORE(fdabi)
  - 0b0000_0001_0001_00

### システム
- NOP(none)
  - 0b0000_0000_0000_00
- SHUTDOWN(none)
  - 0b1111_0000_0000_00
- DEBUG(a)
  - 0b1111_0000_0001_0X
  - X: 0 --> 16進数, 1 --> 10進数

## 命令タイプ

(f)d/a/b(i) | none

- none
  - opecode
- a
  - opecode, reg1 を使用
- da
  - opecode, dest, reg1 を使用
- dab
  - opecode, dest, reg1, reg2 を使用
