import matplotlib.pyplot as plt
datos = [
    {"clave":"ijax","alfabeto":"A1","n":4,"fb_eval":146716,"fb_ms":660.302,"dic_eval":500},
    {"clave":"ans9","alfabeto":"A2","n":4,"fb_eval":17532,"fb_ms":85.648,"dic_eval":500},
    {"clave":"uxyby","alfabeto":"A1","n":5,"fb_eval":9560043,"fb_ms":44015.7,"dic_eval":500},
    {"clave":"r0la7","alfabeto":"A2","n":5,"fb_eval":29780818,"fb_ms":137123.0,"dic_eval":500},
    {"clave":"wpctwv","alfabeto":"A1","n":6,"fb_eval":268293502,"fb_ms":1248450.0,"dic_eval":500},
]

# 1. Fuerza Bruta vs. diccionario
labels = [d["clave"] for d in datos]
fb = [d["fb_eval"] for d in datos]
dic = [d["dic_eval"] for d in datos]
x = list(range(len(labels)))
width = 0.38

fig, ax = plt.subplots()
ax.bar([i-width/2 for i in x], fb, width, label="Fuerza Bruta")
ax.bar([i+width/2 for i in x], dic, width, label="Diccionario")
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.set_xlabel("Clave")
ax.set_ylabel("Candidatos evaluados")
ax.set_title("Fuerza Bruta vs. diccionario")
ax.set_yscale("log")
ax.grid(True, axis="y", alpha=0.25)
ax.legend()
fig.tight_layout()
fig.savefig("results/fb_comparacion_evaluaciones.png", dpi=200)
plt.close(fig)

# 2. Candidatos evaluados vs. n
fig, ax = plt.subplots()
for alf in ["A1", "A2"]:
    serie = [d for d in datos if d["alfabeto"] == alf]
    ax.plot([d["n"] for d in serie], [d["fb_eval"] for d in serie],
            marker="o", label=alf)
    for d in serie:
        ax.annotate(d["clave"], (d["n"], d["fb_eval"]),
                    textcoords="offset points", xytext=(5,5), fontsize=8)
ax.set_xlabel("Longitud n")
ax.set_ylabel("Candidatos evaluados")
ax.set_title("Fuerza Bruta: candidatos evaluados vs. longitud n")
ax.set_yscale("log")
ax.grid(True, alpha=0.25)
ax.legend()
fig.tight_layout()
fig.savefig("results/fb_evaluaciones_vs_n.png", dpi=200)
plt.close(fig)

# 3. Tiempo de ejecución vs. n
fig, ax = plt.subplots()
for alf in ["A1", "A2"]:
    serie = [d for d in datos if d["alfabeto"] == alf]
    ax.plot([d["n"] for d in serie], [d["fb_ms"] for d in serie],
            marker="o", label=alf)
    for d in serie:
        ax.annotate(d["clave"], (d["n"], d["fb_ms"]),
                    textcoords="offset points", xytext=(5,5), fontsize=8)
ax.set_xlabel("Longitud n")
ax.set_ylabel("Tiempo de ejecución (ms)")
ax.set_title("Fuerza Bruta: tiempo de ejecución vs. longitud n")
ax.set_yscale("log")
ax.grid(True, alpha=0.25)
ax.legend()
fig.tight_layout()
fig.savefig("results/fb_tiempo_vs_n.png", dpi=200)
plt.close(fig)

print("Gráficas de Fuerza Bruta generadas correctamente.")