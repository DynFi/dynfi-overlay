catalogues = [
  "adult",
  "advertise",
  "aggressive",
  "alcohol",
  "bank",
  "blog",
  "celebrity",
  "chat",
  "cooking",
  "crypto",
  "cryptocurrency",
  "dangerousmaterial",
  "dating",
  "doh",
  "drugs",
  "education",
  "filterbypass",
  "finance",
  "fortunetelling",
  "forum",
  "fraud",
  "frexamcheaters",
  "gamble",
  "gambling",
  "games",
  "government",
  "hacking",
  "homestyle",
  "hospitals",
  "imagehosting",
  "isp",
  "jobsearch",
  "library",
  "lingerie",
  "malware",
  "manga",
  "military",
  "movies",
  "music",
  "new",
  "news",
  "phone",
  "piracy",
  "podcasts",
  "politics",
  "porn",
  "privacy",
  "radio",
  "reaffected",
  "redirector",
  "religion",
  "remotecontrol",
  "ringtones",
  "science",
  "searchengnines",
  "sexualeducation",
  "shopping",
  "socialmedia",
  "sports",
  "stalkerware",
  "translation",
  "urlshortener",
  "video",
  "vpn",
  "weapons",
  "webmail",
]

template = """
rpz:
    name: "{catalogue}.rpz.dynfi"
    zonefile: "${catalogue}.rpz.dynfi"
    primary: 188.165.99.8
    rpz-log: yes
    rpz-log-name: "{catalogue}-rpz-dynfi"
"""

for c in catalogues:
    open("conf/{}.conf".format(c), "w").write(
        template.format(catalogue=c)
    )
