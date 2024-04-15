from wrap import *
import tkinter as tk
from tkinter import messagebox

def perform_action():
    rc = 0
    try:
        input_array = [int(x) for x in input_array_entry.get().split(' ')]
        
        action = action_var.get()
        
        memory_allocation = int(memory_var.get() == "Выделение памяти с запасом")
        
        if action == "Заполнение числами Фибоначчи":
            if len(input_array) != 1:
                rc = 1
                messagebox.showerror("Ошибка", "Введите корректную длину массива.")
            if rc == 0:
                rc, output_array = fill_in_the_numbers_fibonacci(input_array[0])
        elif action == "Первые вхождения элементов массива":
            rc, output_array = get_the_first_entry_of_elements(input_array, memory_allocation)
        if rc == 0:
            output_array_entry.delete(1.0, tk.END)
            output_array_entry.insert(tk.END, ' '.join(map(str, output_array)))
            messagebox.showinfo("Результат", "Действие выполнено успешно!")
            
    except ValueError:
        messagebox.showerror("Ошибка", "Введите корректный массив целых чисел.")

root = tk.Tk()

input_label = tk.Label(root, text="Введите массив целых чисел или размер для заполнения\nчислами Фибоначчи:")
input_label.pack()

input_array_entry = tk.Entry(root, width=30)
input_array_entry.pack()

action_label = tk.Label(root, text="Выберите действие:")
action_label.pack()

actions = ["Заполнение числами Фибоначчи", "Первые вхождения элементов массива"]
action_var = tk.StringVar(root)
action_var.set(actions[0])

action_menu = tk.OptionMenu(root, action_var, *actions)
action_menu.pack()

memory_label = tk.Label(root, text="Выберите способ выделения памяти для\nзаполнения первыми вхождениями:")
memory_label.pack()

memory_options = ["Выделение памяти с запасом", "Выделение памяти с подсчетом"]
memory_var = tk.StringVar(root)
memory_var.set(memory_options[0])

memory_menu = tk.OptionMenu(root, memory_var, *memory_options)
memory_menu.pack()

perform_button = tk.Button(root, text="Выполнить", command=perform_action)
perform_button.pack()

output_label = tk.Label(root, text="Результат:")
output_label.pack()

output_array_entry = tk.Text(root, height=2, width=30)
output_array_entry.pack()

root.mainloop()
