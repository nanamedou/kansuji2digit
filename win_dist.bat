
set ROOT_DIR = %CD%
cd python

call py -m twine upload --repository pypi dist/*

cd %ROOT_DIR%

