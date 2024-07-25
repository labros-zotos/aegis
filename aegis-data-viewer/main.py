import argparse
import os

from aegis_data import (
    load_data,
    remove_duplicates,
    sort_data,
    plot_temperature,
    plot_humidity,
    plot_sensor_data,
)


parser = argparse.ArgumentParser()
parser.add_argument("--data_path", type=str, default="./data/raw/",
                    help="Path to the data files")
parser.add_argument("--save_path", type=str, default="./plots/",
                    help="Path to save the plots")
parser.add_argument("--plot_type", type=str,
                    choices=["temperature", "humidity"],
                    default="", help="Type of plot to generate")
args = parser.parse_args()


def main():
    if args.data_path[-1] != "/":
        args.data_path += "/"
    df = load_data(args.data_path+"*.csv")

    df = remove_duplicates(df)
    df = sort_data(df)

    if not os.path.exists("temp/data/processed"):
        os.makedirs("temp/data/processed")

    df.to_csv("temp/data/processed/combined.csv", index=False)
    plot_sensor_data(
        df,
        start_date="2022-01-12",
        end_date="2023-05-14",
        save_path=args.save_path + "sensor_data_over_time.png",
    )
    if args.plot_type == "temperature":
        plot_temperature(df, save_path=args.save_path + "temp_over_time.png")
    elif args.plot_type == "humidity":
        plot_humidity(df, save_path=args.save_path + "humidity_over_time.png")


if __name__ == "__main__":
    main()
