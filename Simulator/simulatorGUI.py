import tkinter as tk
import time
import serial
import threading

# 必要に応じてポートとボーレートを変更
# ser = serial.Serial('COM3', 115200, timeout=1)

def start_test():
    try:
        duration = float(entry_duration.get())
        v_min = float(entry_vmin.get())
        v_max = float(entry_vmax.get())
        t_min = float(entry_tmin.get())
        t_max = float(entry_tmax.get())
        interval = float(entry_interval.get())
    except ValueError:
        log.insert(tk.END, "[Error] 数値が正しくありません\n")
        return

    total_steps = int(duration / interval)
    v_step = (v_max - v_min) / total_steps
    t_step = (t_max - t_min) / total_steps

    def send_loop():
        for i in range(total_steps + 1):
            v = v_min + v_step * i
            t = t_min + t_step * i
            msg = f"V={v:.3f},T={t:.2f}"
            try:
                ser.write((msg + '\n').encode())
                response = ser.readline().decode().strip()
            except:
                response = "[UART Error]"
            log.insert(tk.END, f"[{i*interval:.1f}s] Sent: {msg}, Received: {response}\n")
            time.sleep(interval)
    
    # サブスレッドでループ実行（GUIフリーズ防止）
    threading.Thread(target=send_loop, daemon=True).start()

# GUI構築
root = tk.Tk()
root.title("BMS UART送信ソフト")

tk.Label(root, text="テスト時間 [秒]").pack()
entry_duration = tk.Entry(root)
entry_duration.pack()

tk.Label(root, text="電圧範囲 [V]（最小）").pack()
entry_vmin = tk.Entry(root)
entry_vmin.pack()
tk.Label(root, text="電圧範囲 [V]（最大）").pack()
entry_vmax = tk.Entry(root)
entry_vmax.pack()

tk.Label(root, text="温度範囲 [℃]（最小）").pack()
entry_tmin = tk.Entry(root)
entry_tmin.pack()
tk.Label(root, text="温度範囲 [℃]（最大）").pack()
entry_tmax = tk.Entry(root)
entry_tmax.pack()

tk.Label(root, text="送信間隔 [秒]").pack()
entry_interval = tk.Entry(root)
entry_interval.pack()

tk.Button(root, text="スタート", command=start_test).pack(pady=5)

log = tk.Text(root, height=15, width=60)
log.pack(pady=5)

root.mainloop()