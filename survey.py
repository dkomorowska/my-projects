import tkinter as tk


def vote(answer):
    if not survey_ended:
        global answers
        if answer == 1:
            answers[0] += 1
        else:
            answers[1] += 1
        update_results()

def update_results():
    result_1.config(text=f"YES: {answers[0]}", fg="green")
    result_2.config(text=f"NO: {answers[1]}", fg="red")

def end_survey():
    global survey_ended
    survey_ended = True

    for widget in window.winfo_children():
        widget.destroy()

    summary = f"Summary:\nYES: {answers[0]} votes\nNO: {answers[1]} votes"
    summary_label = tk.Label(window, text=summary, font=("Arial", 14))
    summary_label.pack(pady=10)

window = tk.Tk()
window.title("Survey")

survey_ended = False

question = tk.Label(window, text="Do you like dogs?", font=("Arial", 14))
question.pack(pady=10)

button_1 = tk.Button(window, text="YES", width=20, height=2, command=lambda: vote(1))
button_1.pack(pady=5)

button_2 = tk.Button(window, text="NO", width=20, height=2, command=lambda: vote(2))
button_2.pack(pady=5)

answers = [0, 0]
result_1 = tk.Label(window, text="YES: 0", fg="green", font=("Arial", 12))
result_1.pack()

result_2 = tk.Label(window, text="NO: 0", fg="red", font=("Arial", 12))
result_2.pack()

end_button = tk.Button(window, text="End Survey", command=end_survey)
end_button.pack(pady=10)

window.mainloop()

