from building import *

cwd = GetCurrentDir()
src = Glob('*.c')
path = [cwd + '/include']

if GetDepend('PKG_USING_PLL'):
    src += Glob('src/*.c')

group = DefineGroup('PLL', src, depend = ['PKG_USING_PLL'], CPPPATH = path)
