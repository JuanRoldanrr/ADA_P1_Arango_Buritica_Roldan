"""
Genera las gráficas del módulo Backtracking a partir de results/bt_resultados.csv.

"""

import csv
from pathlib import Path
import matplotlib.pyplot as plt


ROOT = Path(__file__).resolve().parents[1]
CSV_PATH = ROOT / "results" / "bt_resultados.csv"
OUT_DIR = ROOT / "results"


def cargar_datos(csv_path: Path):
    if not csv_path.exists():
        raise FileNotFoundError(f"No se encontró el archivo: {csv_path}")

    with csv_path.open("r", encoding="utf-8", newline="") as f:
        rows = list(csv.DictReader(f))

    if not rows:
        raise ValueError("El CSV está vacío.")

    required = {
        "instancia",
        "n",
        "ms_con_poda",
        "ms_sin_poda",
        "nodos_con_poda",
        "nodos_sin_poda",
    }
    missing = required - set(rows[0].keys())
    if missing:
        raise ValueError(f"Faltan columnas en el CSV: {sorted(missing)}")

    return rows

def generar_grafica_tiempo_vs_n(rows):
    n = [int(r["n"]) for r in rows]
    tiempo_con = [float(r["ms_con_poda"]) for r in rows]
    tiempo_sin = [float(r["ms_sin_poda"]) for r in rows]
    etiquetas = [r["instancia"] for r in rows]

    plt.figure(figsize=(11, 6))

    plt.scatter(n, tiempo_con, marker="o", label="Con poda")
    plt.scatter(n, tiempo_sin, marker="x", label="Sin poda")

    # Etiquetas para identificar cada configuración
    for i, etiqueta in enumerate(etiquetas):
        plt.annotate(
            etiqueta,
            (n[i], tiempo_con[i]),
            textcoords="offset points",
            xytext=(5, 5),
            fontsize=8
        )

    plt.xlabel("Tamaño de entrada (n)")
    plt.ylabel("Tiempo de ejecución (ms)")
    plt.title("Backtracking: tiempo de ejecución vs. tamaño de entrada")
    plt.xticks(sorted(set(n)))
    plt.yscale("log")
    plt.legend()
    plt.tight_layout()

    output = OUT_DIR / "bt_tiempo_vs_n.png"
    plt.savefig(output, dpi=180)
    plt.close()

    return output


def generar_grafica_tiempos(rows):
    etiquetas = [r["instancia"] for r in rows]
    con_poda = [float(r["ms_con_poda"]) for r in rows]
    sin_poda = [float(r["ms_sin_poda"]) for r in rows]

    x = range(len(etiquetas))

    plt.figure(figsize=(12, 6))
    plt.plot(x, con_poda, marker="o", label="Con poda")
    plt.plot(x, sin_poda, marker="o", label="Sin poda")
    plt.xticks(list(x), etiquetas, rotation=35, ha="right")
    plt.xlabel("Configuración")
    plt.ylabel("Tiempo de ejecución (ms)")
    plt.title("Backtracking: tiempo de ejecución por configuración")
    plt.legend()
    plt.tight_layout()

    output = OUT_DIR / "bt_tiempos_por_configuracion.png"
    plt.savefig(output, dpi=180)
    plt.close()
    return output


def generar_grafica_nodos(rows):
    etiquetas = [r["instancia"] for r in rows]
    con_poda = [int(r["nodos_con_poda"]) for r in rows]
    sin_poda = [int(r["nodos_sin_poda"]) for r in rows]

    x = range(len(etiquetas))

    plt.figure(figsize=(12, 6))
    plt.plot(x, con_poda, marker="o", label="Nodos con poda")
    plt.plot(x, sin_poda, marker="o", label="Nodos sin poda")
    plt.xticks(list(x), etiquetas, rotation=35, ha="right")
    plt.xlabel("Configuración")
    plt.ylabel("Nodos visitados")
    plt.title("Backtracking: nodos visitados con poda vs. sin poda")
    plt.legend()
    plt.tight_layout()

    output = OUT_DIR / "bt_nodos_poda_vs_sin_poda.png"
    plt.savefig(output, dpi=180)
    plt.close()
    return output


def main():
    rows = cargar_datos(CSV_PATH)
    time_vs_n = generar_grafica_tiempo_vs_n(rows)
    time_output = generar_grafica_tiempos(rows)
    nodes_output = generar_grafica_nodos(rows)

    print("Gráficas generadas correctamente:")
    print(f"- {time_vs_n}")
    print(f"- {time_output}")
    print(f"- {nodes_output}")


if __name__ == "__main__":
    main()