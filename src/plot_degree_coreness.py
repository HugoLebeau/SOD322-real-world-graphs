import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("../outputs/degree_coreness_scholar.csv")
ID = pd.read_csv("../data/scholar/ID.txt", sep='$', header=None)
ID = ID[0].apply(lambda s: ' '.join(s.split(" ")[1:]))
ID.name = "Name"

df.plot.scatter(x="Degree", y="Coreness", edgecolor=[])
plt.grid(ls=':')
plt.show()

print(ID.loc[df[df["Coreness"] == 14]["ID"].values])
