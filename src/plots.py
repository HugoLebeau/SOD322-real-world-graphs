import pandas as pd
import matplotlib.pyplot as plt

# %% tme2-1 Average degree density and Edge density

df_amazon = pd.read_csv("../outputs/densest_prefix_com-amazon.csv")
df_lj = pd.read_csv("../outputs/densest_prefix_com-lj.csv")
df_orkut = pd.read_csv("../outputs/densest_prefix_com-orkut.csv")

for df, title in [(df_amazon, "com-Amazon"), (df_lj, "com-LiveJournal"), (df_orkut, "com-Orkut")] :
    fig, ax = plt.subplots(1, 2, figsize=(10, 4))
    fig.suptitle(title+" — Densest core ordering prefix")
    df.plot(x="Size", y="Average degree density", ax=ax[0], legend=None)
    ax[0].grid(ls=':')
    ax[0].set_xscale('log')
    ax[0].set_title("Average degree density")
    df.plot(x="Size", y="Edge density", ax=ax[1], legend=None)
    ax[1].grid(ls=':')
    ax[1].set_xscale('log')
    ax[1].set_title("Edge density")
    plt.show()

# %% tme2-2 Coreness vs. Degree

df = pd.read_csv("../outputs/degree_coreness_scholar.csv")
ID = pd.read_csv("../data/scholar/ID.txt", sep='$', header=None)
ID = ID[0].apply(lambda s: ' '.join(s.split(" ")[1:]))
ID.name = "Name"

df.plot.scatter(x="Degree", y="Coreness", edgecolor=[])
plt.grid(ls=':')
plt.title("Google Scholar")
plt.show()

print(ID.loc[df[df["Coreness"] == 14]["ID"].values])
