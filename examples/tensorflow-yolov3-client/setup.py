from distutils.core import setup, Extension
from Cython.Build import cythonize
moudle_list = ['yolov3ClientModule.py','utils.py']
extension_list = [Extension(name=each[:-3],sources=[each]) for each in moudle_list]
setup(
    ext_modules = cythonize(extension_list)
)