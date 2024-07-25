import matplotlib.pyplot as plt
import matplotlib.dates as mdates


def plot_temperature(df, save_path=None):
    plt.figure(figsize=(10, 6))
    plt.plot(df["datetime"], df["temperature"], label="Temperature")
    plt.xlabel("Datetime")
    plt.ylabel("Temperature")
    plt.title("Temperature")
    plt.legend()
    if save_path:
        plt.savefig(save_path)
    plt.show()


def plot_humidity(df, save_path=None):
    plt.figure(figsize=(10, 6))
    plt.plot(df["datetime"], df["humidity"], label="Humidity", color="orange")
    plt.xlabel("Datetime")
    plt.ylabel("Humidity")
    plt.title("Humidity")
    plt.legend()
    if save_path:
        plt.savefig(save_path)
    plt.show()


def plot_pump_status(df, save_path=None):
    plt.figure(figsize=(10, 6))
    plt.plot(df["datetime"], df["pump_status"], label="Pump Status",
             color="green")
    plt.xlabel("Datetime")
    plt.ylabel("Pump Status")
    plt.title("Pump Status")
    plt.legend()
    if save_path:
        plt.savefig(save_path)
    plt.show()


def plot_sensor_data(df, start_date=None, end_date=None, save_path=None):
    if start_date:
        df = df[df["datetime"] >= start_date]
    if end_date:
        df = df[df["datetime"] <= end_date]

    fig, axs = plt.subplots(3, 1, figsize=(12, 18), sharex=True)

    axs[0].plot(df["datetime"], df["temperature"], label="Temperature")
    axs[0].set_ylabel("Temperature")
    axs[0].set_title("Temperature")
    axs[0].legend()

    axs[1].plot(df["datetime"], df["humidity"], label="Humidity",
                color="orange")
    axs[1].set_ylabel("Humidity")
    axs[1].set_title("Humidity")
    axs[1].legend()

    axs[2].plot(df["datetime"], df["pump_status"], label="Pump Status",
                color="green")
    axs[2].set_ylabel("Pump Status")
    axs[2].set_title("Pump Status")
    axs[2].legend()

    axs[2].set_xlabel("Datetime")
    axs[2].xaxis.set_major_formatter(mdates.DateFormatter("%d/%m/%Y %H:%M"))
    axs[2].xaxis.set_major_locator(mdates.AutoDateLocator())

    if save_path:
        plt.savefig(save_path)
    plt.show()
