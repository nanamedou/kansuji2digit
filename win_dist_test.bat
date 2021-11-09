
set ROOT_DIR = %CD%
cd python

call py -m build
call py -m twine upload --repository testpypi dist/*

cd %ROOT_DIR%

call py -m pip install -U -i https://test.pypi.org/simple/ kansuji2digit 

call py -m kansuji2digit


