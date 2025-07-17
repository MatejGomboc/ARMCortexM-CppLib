import lit.formats
import os

config.name = 'asm-tests'
config.test_format = lit.formats.ShTest()
config.suffixes = ['.cpp']
config.environment['PATH'] = os.environ['PATH']
config.test_source_root = os.path.dirname(__file__)
config.test_exec_root = os.path.dirname(__file__) + "/../build/asm_tests/"
