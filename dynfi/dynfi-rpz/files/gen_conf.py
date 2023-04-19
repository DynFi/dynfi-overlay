catalogues = [
"advertise",
"aggressive",
"alcohol",
"bank",
"blog",
"celebrity",
"chat",
"cooking",
"crypto",
"dangerousmaterial",
"dating",
"doh",
"drugs",
"education",
"filterbypass",
"finance",
"fortunetelling",
"forum",
"frexamcheaters",
"fraud",
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
"malware",
"manga",
"military",
"movies",
"music",
"news",
"phone",
"piracy",
"podcasts",
"porn",
"pornsmall",
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
"translation",
"urlshortener",
"video",
"vpn",
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
