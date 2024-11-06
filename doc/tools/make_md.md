# make_md.py 笔记

## 标记

`【覆写】`：重写已有函数或实现
`【新增】`：新增函数或实现

## 变量对应

- 类
  `class_name`：大小写敏感的变量名
  `f"class_{class_name.lower()}.md"`：类文件名
  `f"/class/class_{class_name.lower()}.md"`：类文件绝对路径
- 类组
  `CLASS_GROUPS_BASE[group_name]`：大小写敏感的类组名
  `f"class_{CLASS_GROUPS_BASE[group_name].lower()}.md"`：类组文件名
  `f"/class/class_{CLASS_GROUPS_BASE[group_name].lower()}.md"`：类组文件绝对路径
