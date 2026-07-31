# 🎶 chimmusicplayer

**chimmusicplayer** là một trình phát nhạc trên dòng lệnh (TUI) mạnh mẽ, được tùy biến từ [`kew`](https://github.com/ravachol/kew). Ngoài việc phát nhạc offline với giao diện terminal đẹp mắt, ứng dụng còn tích hợp **tìm kiếm và tải nhạc trực tiếp từ YouTube**, tự động nhúng ảnh bìa và thông tin bài hát.

![chimmusicplayer](images/kew.png)

---

## 🚀 Tính năng nổi bật

- **🔍 Tìm kiếm YouTube (F5):** Tìm nhạc trực tiếp trên YouTube, hiển thị kết quả ngay trong app.
- **⬇️ Tải MP3 tự động:** Tải âm thanh chất lượng cao về thư mục `~/Music`.
- **🖼️ Metadata & Thumbnail:** Tự động nhúng ảnh bìa, tên bài hát, nghệ sĩ vào file MP3.
- **📴 Hoạt động Offline:** Bài đã tải nghe lại bất cứ lúc nào, không cần mạng.
- **🎨 Giao diện TUI:** Hiển thị ảnh bìa trong terminal, visualizer âm thanh, hỗ trợ theme tùy biến.
- **📚 Thư viện tự động:** Tự dò thư mục nhạc theo nhiều ngôn ngữ (Music, Música, Musique, 音楽…).

---

## 🛠 Yêu cầu hệ thống

### Công cụ ngoài
| Công cụ | Vai trò | Cài đặt (Arch Linux) |
| :--- | :--- | :--- |
| **yt-dlp** | Tìm kiếm & tải nhạc từ YouTube | `sudo pacman -S yt-dlp` |
| **ffmpeg** | Chuyển đổi âm thanh sang MP3 | `sudo pacman -S ffmpeg` |

### Thư viện phụ thuộc
```bash
sudo pacman -S taglib opus opusfile libvorbis libogg glib2 chafa fftw faad2 gdk-pixbuf2
```

> **Lưu ý:** `opusfile` là bắt buộc — nếu thiếu, ứng dụng sẽ báo lỗi
> `error while loading shared libraries: libopusfile.so.0`.

---

## 🔨 Cài đặt & Biên dịch

```bash
git clone https://github.com/Hdoanf/chimmusicplayer.git
cd chimmusicplayer
```

### Cách 1 — CMake (khuyên dùng)
```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

### Cách 2 — Makefile
```bash
make -j$(nproc)
sudo make install
```

Sau khi cài, chạy bằng lệnh:
```bash
chimmusicplayer
```

---

## ⌨️ Phím tắt cơ bản

| Phím | Hành động |
| :--- | :--- |
| **F5** / **Shift + Y** | Mở màn hình YouTube & tìm kiếm |
| **Enter** | Chọn bài và phát |
| **Tab** | Chuyển View (Playlist / Library / YouTube / Help) |
| **Space** | Tạm dừng / Tiếp tục |
| **H** / **L** | Bài trước / Bài kế tiếp |
| **Q** / **Esc** | Thoát |

---

## 📁 Cấu hình

| Tệp | Đường dẫn |
| :--- | :--- |
| Cấu hình chính | `~/.config/chimmusicplayer/chimmusicplayerrc` |
| Trạng thái / phiên | `~/.config/chimmusicplayer/chimmusicplayerstaterc` |
| Thư mục nhạc mặc định | `~/Music` |

Bạn có thể tùy chỉnh phím tắt, màu sắc và thư mục nhạc trong tệp cấu hình chính.

---

## 🤝 Đóng góp

Mọi ý kiến đóng góp hoặc báo lỗi xin tạo **Issue** hoặc gửi **Pull Request** trên GitHub.

*Phát triển bởi **Hdoanf** — dựa trên dự án gốc [kew](https://github.com/ravachol/kew) của ravachol.*
