
dirEngineBuildScripts = '../Tools/Build'
dirGameBuildScripts = '.'

import sys, os, collections

sys.path.append(dirEngineBuildScripts)
import Utility
import GuguEngine


def Main():
    
    # Setup
    dirCurrent = os.getcwd()
    os.chdir(dirGameBuildScripts)

    aActions = { 'premake' }
    
    # Menu : Compilers
    aCompilers = []
    if any(x in ['premake'] for x in aActions):
        dictChoices = collections.OrderedDict()
        dictChoices['vs2013'] = 'Visual 2013'
        dictChoices['vs2015'] = 'Visual 2015'
        dictChoices['vs2017'] = 'Visual 2017'
        dictChoices['gmake'] = 'GNU Makefiles'
        dictChoices['xcode4'] = 'XCode'
        dictChoices['codelite'] = 'CodeLite'
        aCompilers = Utility.PromptMenu('Select Compilers', dictChoices, True)

    # Premake
    for compiler in aCompilers:
        if 'premake' in aActions:
            GuguEngine.Premake(dirEngineBuildScripts, 'BuildGame.lua', compiler)

    # Finalize
    os.chdir(dirCurrent)

    print('')
    input('Press Enter to close.')


Main()
