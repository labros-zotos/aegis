def remove_duplicates(df):
    return df.drop_duplicates(subset="datetime")


def sort_data(df):
    return df.sort_values(by="datetime")
