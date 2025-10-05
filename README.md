# 🔧 Pipex Cheat Sheet

## 📌 Proje Özeti
**Amaç:** Shell'deki pipe mekanizmasını implement etmek
```bash
./pipex infile cmd1 cmd2 outfile
# Eşdeğeri: < infile cmd1 | cmd2 > outfile
```

---

## 🔑 Temel Kavramlar

### File Descriptor (fd)
- Dosyaları ve pipe'ları temsil eden sayılar
- **0** = STDIN (standart girdi, klavye)
- **1** = STDOUT (standart çıktı, ekran)
- **2** = STDERR (hata çıktısı)

### Process
- Çalışan bir program
- **Parent process:** Ana program
- **Child process:** `fork()` ile oluşturulan kopya

---

## 🛠️ Sistem Çağrıları

### 1️⃣ `fork()` - Process Oluşturma
```c
pid_t pid = fork();

if (pid == 0) {
    // Child process burası
} else if (pid > 0) {
    // Parent process burası
} else {
    // Hata durumu
}
```
**Ne yapar?**
- Mevcut process'in kopyasını oluşturur
- Parent'ta: child'ın PID'sini döndürür
- Child'da: 0 döndürür

---

### 2️⃣ `pipe()` - Boru Oluşturma
```c
int fd[2];
pipe(fd);

// fd[0] = okuma ucu (read end)
// fd[1] = yazma ucu (write end)
```
**Ne yapar?**
- İki process arası iletişim için boru oluşturur
- Bir uçtan yazılan diğer uçtan okunur

**Kullanım:**
```c
write(fd[1], "hello", 5);  // Pipe'a yaz
read(fd[0], buffer, 5);     // Pipe'tan oku
```

---

### 3️⃣ `dup2()` - File Descriptor Yönlendirme
```c
dup2(eski_fd, yeni_fd);
```
**Ne yapar?**
- `yeni_fd`'yi `eski_fd` ile değiştirir
- Artık `yeni_fd` kullanıldığında `eski_fd` işlem görür

**Örnek:**
```c
int file = open("output.txt", O_WRONLY);
dup2(file, STDOUT_FILENO);  // STDOUT → output.txt
printf("Bu yazı ekran yerine dosyaya gidecek");
```

**Pipex'te kullanım:**
```c
// Child 1: ls -l'nin çıktısını pipe'a yönlendir
dup2(fd[1], STDOUT_FILENO);

// Child 2: wc -l'in girdisini pipe'tan al
dup2(fd[0], STDIN_FILENO);
```

---

### 4️⃣ `execve()` - Program Çalıştırma
```c
execve(path, argv, envp);
```
**Parametreler:**
- `path`: Program yolu (örn: "/bin/ls")
- `argv`: Komut ve argümanları (NULL ile biten array)
- `envp`: Environment değişkenleri

**Örnek:**
```c
char *argv[] = {"ls", "-l", NULL};
char *envp[] = {NULL};
execve("/bin/ls", argv, envp);
// Bu satıra GELMİYOR! execve mevcut process'i değiştirir
```

**❗ Önemli:** 
- `execve` başarılı olursa GERİ DÖNMEZ
- Sadece hata durumunda -1 döner

---

### 5️⃣ `wait()` / `waitpid()` - Child Bekleme
```c
wait(NULL);           // Herhangi bir child'ın bitmesini bekle
waitpid(pid, &status, 0);  // Belirli bir child'ı bekle
```
**Ne yapar?**
- Parent process, child process'in bitmesini bekler
- Zombie process'leri önler

---

### 6️⃣ `open()` - Dosya Açma
```c
int fd = open("dosya.txt", flags, mode);
```
**Flags:**
- `O_RDONLY` - Sadece okuma
- `O_WRONLY` - Sadece yazma
- `O_CREAT` - Dosya yoksa oluştur
- `O_TRUNC` - Dosyayı temizle
- `O_APPEND` - Sona ekle

**Örnek:**
```c
// Okuma için
int infile = open("input.txt", O_RDONLY);

// Yazma için (yoksa oluştur, varsa temizle)
int outfile = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
```

---

### 7️⃣ `close()` - Dosya Kapatma
```c
close(fd);
```
**Ne yapar?**
- File descriptor'ı kapatır
- **Önemli:** Kullanmadığın pipe uçlarını kapat!

**Neden önemli?**
```c
// Child 1: yazma ucu kullanıyor, okuma ucunu kapatmalı
close(fd[0]);

// Child 2: okuma ucu kullanıyor, yazma ucunu kapatmalı
close(fd[1]);
```

---

### 8️⃣ `perror()` - Hata Mesajı
```c
perror("Hata açıklaması");
```
**Ne yapar?**
- Son sistem çağrısının hatasını yazdırır
- Errno değerine göre mesaj üretir

**Örnek:**
```c
if (open("dosya.txt", O_RDONLY) == -1) {
    perror("pipex");  // "pipex: No such file or directory"
}
```

---

### 9️⃣ `access()` - Dosya Erişim Kontrolü
```c
if (access("dosya.txt", F_OK) == 0) {
    // Dosya var
}
```
**Flags:**
- `F_OK` - Dosya var mı?
- `R_OK` - Okunabilir mi?
- `W_OK` - Yazılabilir mi?
- `X_OK` - Çalıştırılabilir mi?

---

## 🎯 Pipex İş Akışı

```
1. pipe(fd) oluştur
2. fork() ile child1 oluştur
   └─ Child1:
      • infile'ı aç
      • dup2(infile, STDIN)
      • dup2(fd[1], STDOUT)
      • close tüm fd'ler
      • execve(cmd1)
      
3. fork() ile child2 oluştur
   └─ Child2:
      • outfile'ı aç
      • dup2(fd[0], STDIN)
      • dup2(outfile, STDOUT)
      • close tüm fd'ler
      • execve(cmd2)
      
4. Parent:
   • close(fd[0])
   • close(fd[1])
   • wait() × 2 (her iki child için)
```

---

## ⚠️ Önemli Kurallar

### ✅ DO (Yapılması Gerekenler)
- Her `open()`'dan sonra hata kontrolü
- Her `fork()`'tan sonra hata kontrolü
- Kullanmadığın pipe uçlarını **mutlaka** kapat
- `dup2()`'den sonra orijinal fd'yi kapat
- Parent'ta tüm fd'leri kapat
- Tüm child'ları `wait()` ile bekle
- Memory leak olmamalı (`malloc` ise `free`)

### ❌ DON'T (Yapılmaması Gerekenler)
- Pipe uçlarını kapatmayı unutma (program asılır kalır)
- `execve`'den sonra kod yazma (zaten çalışmaz)
- Child'larda parent'ın fd'lerini açık bırakma
- Hata kontrolü yapmadan devam etme

---

## 🐛 Hata Yönetimi

### Dosya Bulunamazsa
```c
int fd = open(file, O_RDONLY);
if (fd < 0) {
    perror("pipex");
    exit(1);
}
```

### Komut Bulunamazsa
```c
if (execve(path, argv, envp) == -1) {
    perror("pipex");
    exit(127);  // Command not found
}
```

### Fork Başarısızsa
```c
pid_t pid = fork();
if (pid < 0) {
    perror("fork");
    exit(1);
}
```

---

## 📝 Bonus: Multiple Pipes

```bash
./pipex file1 cmd1 cmd2 cmd3 file2
# Eşdeğeri: < file1 cmd1 | cmd2 | cmd3 > file2
```

**Mantık:**
- n komut için (n-1) pipe gerekir
- Her child, bir önceki pipe'tan okur ve bir sonraki pipe'a yazar
- İlk child infile'dan okur
- Son child outfile'a yazar

---

## 🧠 Hatırlatmalar

1. **fd[0]** = okuma ucu = **INPUT** gelir
2. **fd[1]** = yazma ucu = **OUTPUT** gider
3. **STDIN** = 0, **STDOUT** = 1, **STDERR** = 2
4. `execve` başarılı olursa GERİ DÖNMEZ
5. Shell'in davranışını taklit et (hata mesajları dahil)
6. Zombie process'leri önlemek için `wait()` kullan
7. Tüm fd'leri düzgün kapat

---

## 🔍 Debug İpuçları

```c
// Hangi process'te olduğunu görmek için
printf("PID: %d\n", getpid());

// Pipe içeriğini kontrol etmek için
write(fd[1], "test\n", 5);

// fd'lerin açık olup olmadığını kontrol
// valgrind --leak-check=full --track-fds=yes ./pipex ...
```

---

**Kaynak:** Pipex Project (42 School)  
**Versiyon:** 4.0