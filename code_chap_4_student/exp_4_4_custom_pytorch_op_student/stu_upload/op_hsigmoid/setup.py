from setuptools import setup
from torch.utils import cpp_extension

setup(
    # TODO: 给出编译后的链接库名称
    name="hsigmoid_extension",
    ext_modules=[
        cpp_extension.CppExtension(
            # TODO：以正确的格式给出编译文件即编译函数
            name="hsigmoid_extension",  # 这是此扩展模块的名称
            sources=["hsigmoid.cpp"],  # 这里列出所有需要编译的源代码文件
        )
    ],
    # 执行编译命令设置
    cmdclass={"build_ext": cpp_extension.BuildExtension},
)
print("generate .so PASS!\n")
