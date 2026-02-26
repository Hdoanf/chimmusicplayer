# 🎶 chimmusicplayer

**chimmusicplayer** là một trình phát nhạc trên dòng lệnh (TUI) mạnh mẽ, được tùy biến từ `kew`. Ứng dụng không chỉ phát nhạc offline mà còn tích hợp khả năng tìm kiếm và tải nhạc trực tiếp từ YouTube với đầy đủ ảnh bìa và thông tin bài hát.

---

## 🚀 Tính năng nổi bật

-   **Tìm kiếm YouTube (F5):** Tìm kiếm nhạc trực tiếp trên YouTube và hiển thị kết quả ngay trong ứng dụng.
-   **Tải MP3 tự động:** Tự động tải âm thanh chất lượng cao về thư mục `~/Music`.
-   **Metadata & Thumbnail:** Tự động nhúng ảnh bìa, tên bài hát, nghệ sĩ từ YouTube vào file MP3.
-   **Hoạt động Offline:** Sau khi bài hát được tải về, bạn có thể nghe lại bất cứ lúc nào mà không cần mạng.

---

## 🛠 Yêu cầu hệ thống

Để ứng dụng hoạt động hoàn hảo, bạn cần cài đặt các công cụ sau:

1.  **yt-dlp:** Để tìm kiếm và tải nhạc.
    ```bash
    sudo curl -L https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp -o /usr/local/bin/yt-dlp
    sudo chmod a+rx /usr/local/bin/yt-dlp
    ```
2.  **ffmpeg:** Để chuyển đổi âm thanh sang định dạng MP3.
    ```bash
    sudo pacman -S ffmpeg  # Arch Linux
    ```
3.  **Các thư viện phát nhạc:** `taglib`, `opus`, `vorbis`, `glib2`, `chafa`, `fftw`, `faad2`.

---

## 🔨 Cài đặt và Biên dịch

Bạn có thể biên dịch ứng dụng bằng một trong hai cách sau:

### Cách 1: Sử dụng CMake (Khuyên dùng)

```bash
git clone https://github.com/Hdoanf/chimmusicplayer.git
cd chimmusicplayer
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

### Cách 2: Sử dụng Makefile truyền thống

```bash
git clone https://github.com/Hdoanf/chimmusicplayer.git
cd chimmusicplayer
make -j$(nproc)
sudo make install
```

---

## ⌨️ Các phím tắt cơ bản

| Phím tắt | Hành động |
| :--- | :--- |
| **F5** | Mở màn hình YouTube / Bắt đầu tìm kiếm |
| **Enter** | Chọn bài hát và phát nhạc |
| **Tab** | Chuyển đổi giữa các View (Playlist, Library, YouTube, Help) |
| **Shift + Y** | Phím tắt nhanh mở YouTube |
| **Space** | Tạm dừng / Tiếp tục phát |
| **H / L** | Bài trước / Bài kế tiếp |
| **Q / Esc** | Thoát ứng dụng |

---

## 📁 Cấu hình

Tệp cấu hình được lưu tại: `~/.config/chimmusicplayer/chimmusicplayerrc`

Bạn có thể tùy chỉnh phím tắt, màu sắc và thư mục nhạc mặc định tại đây.

---

## 🤝 Đóng góp

Mọi ý kiến đóng góp hoặc báo lỗi xin vui lòng tạo **Issue** hoặc gửi **Pull Request** trên GitHub.

*Phát triển bởi Hdoanf - Dựa trên dự án gốc kew.*
