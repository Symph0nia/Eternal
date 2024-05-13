#!/bin/bash

# 指定包含可执行文件的目录
EMBED_DIR="../embed"
OUTPUT_H="../bind/bind_files.h"
OUTPUT_C="../bind/bind_files.c"

# 创建输出目录，如果不存在
mkdir -p ../bind

# 清理之前生成的输出文件
rm -f $OUTPUT_H $OUTPUT_C

# 生成头文件
echo "#ifndef BIND_FILES_H" > $OUTPUT_H
echo "#define BIND_FILES_H" >> $OUTPUT_H
echo "#include <stddef.h>" >> $OUTPUT_H

# 生成源文件
echo "#include \"bind_files.h\"" > $OUTPUT_C

# 将文件转换为C数组的函数
convert_to_c_array() {
    local file_path=$1
    local file_name=$(basename $file_path)
    local var_name=$(echo $file_name | tr -cd '[:alnum:]_')

    echo "extern const unsigned char ${var_name}[];" >> $OUTPUT_H
    echo "extern const size_t ${var_name}_size;" >> $OUTPUT_H

    # 使用 xxd 将文件转换为 C 数组，并移除自动生成的结束括号
    echo "const unsigned char ${var_name}[] = {" >> $OUTPUT_C
    xxd -i $file_path | sed '1d;$d' | sed '$d' >> $OUTPUT_C
    echo "};" >> $OUTPUT_C

    local file_size=$(stat -c%s "$file_path")
    echo "const size_t ${var_name}_size = ${file_size};" >> $OUTPUT_C
}

# 处理EMBED_DIR中的文件
file="$EMBED_DIR/eternal"
if [ -f "$file" ]; then
    convert_to_c_array "$file"
else
    echo "文件 $file 不存在"
fi

echo "#endif // BIND_FILES_H" >> $OUTPUT_H
