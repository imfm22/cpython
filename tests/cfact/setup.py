""" Python 调用 C 实现的阶乘函数
# 编译
```python
python setup.py build
```
# 测试
进入 `build/lib.<linux-platform>/`
进入 python 环境运行下列命令

```python
from cfact import factorial
factorial(10)
```
"""
from distutils.core import setup, Extension

factorial_module = Extension('cfact', sources = ['cfact.c'])
setup(name = 'MathExtension',
      version = '1.0',
      description = 'This is a math packages',
      ext_modules = [factorial_module]
      )
