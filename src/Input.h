#ifndef INPUT_H
#define INPUT_H

// Cac lenh nguoi choi co the ra. Game chi hieu Command, khong can biet la phim nao.
// Muon doi phim hoac them phim moi: chi sua lop Input.
enum class Command {
    Left, Right, Rotate, SoftDrop, HardDrop, Pause, Restart, Quit
};

class Input {
public:
    // Doc phim NEU dang co, KHONG dung cho.
    // Tra ve true va ghi vao 'cmd' neu doc duoc mot phim co y nghia.
    // Tra ve false khi khong con phim nao (phim la bi bo qua).
    bool poll(Command& cmd);
};

#endif
