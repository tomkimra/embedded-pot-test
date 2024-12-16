# 組込みソフトウェアのテストサンプル


## 環境

* CMake 3.10以降
* lcov

## ビルド

フォルダごとにcmake設定が異なるので，それぞれのディレクトリに移動してから下記コマンドを実行する．

**ビルド準備**

```shell
cmake -S . -B build
```

**ビルド**

```shell
cmake --build build
```

**テスト**

```shell
./run_test.sh # step1,2
# もしくは
./run_test_coverage.sh # step2,3
```
### VSCodeの場合

**ビルド準備**

- コマンドパレットで `CMake: Configure` を選択
- `${workspaceFolder}/step1/CMakeLists.txt` を選択

**別のCMakeLists.txtで行う場合**

- `.vscode/settings.json`のcmake.sourceDirectoryをstep2,step3に変更してからコマンドパレットの `CMake: Delete Cache and Reconfigure` を選択

**ビルド**

- コマンドパレットで `CMake: Build`

