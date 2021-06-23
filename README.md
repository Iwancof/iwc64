
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
- ADD(3reg)
  - 0b0000_0000_0001_00
- SUB(3reg)
  - 0b0000_0000_0010_00

### システム
- NOP(no_arg)
  - 0b0000_0000_0000_00
- SHUTDOWN(no_arg)
  - 0b1111_1111_1111_00

## 命令タイプ

- no_arg
  - opecode
- 2reg
  - opecode, dest, reg1 を使用
- 3reg
  - opecode, dest, reg1, reg2 を使用
