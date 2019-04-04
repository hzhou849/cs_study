# -*- mode: python -*-

block_cipher = None


a = Analysis(['start_Gpio.py'],
             pathex=['/home/howardz/Development/Ubuntu_x86/Kontron_Driver_Project_Development/Kontron_GPIO_gui_development_final'],
             binaries=[],
             datas=[],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          name='start_Gpio',
          debug=False,
          strip=False,
          upx=True,
          runtime_tmpdir=None,
          console=True )
