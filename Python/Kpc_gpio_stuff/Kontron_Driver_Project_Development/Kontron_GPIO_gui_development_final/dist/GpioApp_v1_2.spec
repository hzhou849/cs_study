# -*- mode: python -*-

block_cipher = None


a = Analysis(['GpioApp_v1_2.py'],
             pathex=['/home/howardz/dev_repositories/development_source/ubuntu_dev/tower_button_box_project/Kontron_Driver_Project_Development/Kontron_GPIO_gui_development_final/dist'],
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
          name='GpioApp_v1_2',
          debug=False,
          strip=False,
          upx=True,
          runtime_tmpdir=None,
          console=True )
