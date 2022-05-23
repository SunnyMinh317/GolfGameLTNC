# Mini Golf A++
## Giới thiệu
Mini Golf A++ là một game mini golf đơn giản làm bằng thư viện SDL2 (bao gồm SDL, SDL_image, SDL_mixer, SDL_ttf) và C++


<p float="left">
  <img src="https://user-images.githubusercontent.com/90145990/169738792-8e0d0b50-e827-4674-be50-3d88ac1249e5.png" width="500" />
  <img src="https://user-images.githubusercontent.com/90145990/169738796-b55f0349-0cdd-4e15-8207-d35cd106686e.png" width="500" /> 
</p>

## Chạy project

### Bước 1:
Sau khi cài đặt SDL2, SDL2_image, SDL2_mixer, SDL2_ttf, chạy lệnh sau trong CMD trong folder chứa các file .cpp. File GolfGame.exe sẽ xuất hiện. 
```cmd
g++ -IC:\SDL2\include -IC:\SDL2_image-2.0.5\include -IC:\SDL2_mixer-2.0.4\include -IC:\SDL2_ttf-2.0.18\include -LC:\SDL2\lib\x64 -LC:\SDL2_image-2.0.5\lib\x64 -LC:\SDL2_mixer-2.0.4\lib\x64 -LC:\SDL2_ttf-2.0.18\lib\x64 Ball.cpp Hole.cpp main.cpp Mouse.cpp Scoreboard.cpp Texture.cpp Tile.cpp Timer.cpp  -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o GolfGame
```
#### Lưu ý
Các đường dẫn folder include và lib của các thư viện SDL2 có thể khác nhau tùy cách cài đặt mỗi máy.

### Bước 2:
Chạy chương trình GolfGame.exe
```cmd
GolfGame.exe
```

## Phân công công việc
<b>Tạo cấu trúc tổng thể chương trình:</b> Huy Bình </br>
<b>UI</b>: Nhật Minh, Yến Nhi</br>
<b>Tile system</b>: Yến Nhi</br>
<b>Map design</b>: Nhật Minh</br>
<b>Physics chính</b>: Huy Bình, Nhật Minh</br>
<b>Scoreboard</b>: Huy Bình</br>


