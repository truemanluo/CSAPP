7.1

| 符号 | .systab条目 | 符号类型 | 在哪个模块中定义 | 节 |
| :----:  | :----: | :----:  | :----: | :----: |
| buf | yes | 外部 | **m.o** | .data |
| bufp0 | yes | 全局 | swap.o | .data |
| bufp1 | yes | 全局 | swap.o | COMMON |
| swap | yes | 全局 | swap.o | **.text** |
| temp | no |  | |  |

7.3

1. `gcc p.o libx.a`

2. `gcc p.o libx.a liby.a`

3. `gcc p.o libx.a liby.a libx.a`