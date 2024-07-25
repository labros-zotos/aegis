import pandas as pd
import glob


def load_data(path):
    csv_files = glob.glob(path)
    print(path)
    data_frames = [
        pd.read_csv(file, header=None, delimiter=",",
                    names=["datetime", "temperature", "humidity",
                           "barometric_pressure", "pump_status",
                           "pump_last_on", "pump_last_off"])
        for file in csv_files
    ]
    print(data_frames)
    combined_df = pd.concat(data_frames, ignore_index=True)
    combined_df["datetime"] = pd.to_datetime(combined_df["datetime"])
    return combined_df
