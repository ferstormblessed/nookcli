import click
import os
import shutil

TEMPLATES_DIR = "templates"

TEMPLATES = {
    "platformer": os.path.join(TEMPLATES_DIR, "platformer_template.cpp"),
    "infinite runner": os.path.join(TEMPLATES_DIR, "infinite_runner_template.cpp"),
    "pong": os.path.join(TEMPLATES_DIR, "pong_template.cpp"),
    "default": None
}

# Configuración por defecto
DEFAULT_CONFIG = {
    "WINDOW_TITLE": "NOOK",
    "WIDTH": "1280",
    "HEIGHT": "720",
    "FRAMES": "60",
    "ASSETS_PATH": "./Assets",
    "AUDIO_DIRECTORY": "/Audio",
    "FONTS_DIRECTORY": "/Fonts",
    "SPRITES_DIRECTORY": "/Sprites",
    "GRAVITY": "10.0",
    "HIT_THRESHOLD": "0.01"
}

PLACE_TO_INSERT_TEMPLATE = "// TEMPLATE"


@click.command()
@click.option("-t", "--template",
              type=click.Choice(list(TEMPLATES.keys()), case_sensitive=False),
              help="Template to use for the project.")
def create_project(template):
    # Pedir al usuario que seleccione un template si no se proporciona
    if template is None:
        template = click.prompt(
                "Choose a template",
                type=click.Choice(list(TEMPLATES.keys()),
                                  case_sensitive=False))

    # Recoger la configuración del usuario o usar los valores por defecto
    window_title = click.prompt(
            "Window Title",
            default=DEFAULT_CONFIG["WINDOW_TITLE"])
    width = click.prompt(
            "Width",
            default=DEFAULT_CONFIG["WIDTH"])
    height = click.prompt(
            "Height",
            default=DEFAULT_CONFIG["HEIGHT"])
    frames = click.prompt(
            "Frames",
            default=DEFAULT_CONFIG["FRAMES"])
    gravity = click.prompt(
            "Gravity",
            default=DEFAULT_CONFIG["GRAVITY"])
    hit_threshold = click.prompt(
            "Hit Threshold",
            default=DEFAULT_CONFIG["HIT_THRESHOLD"])

    # Leer y personalizar main.cpp
    main_template_path = os.path.join(TEMPLATES_DIR, "main_template.cpp")
    with open(main_template_path, "r") as main_template_file:
        main_content = main_template_file.read()

    # Insertar el template específico si no es "default"
    if template.lower() != "default":
        template_file = TEMPLATES[template.lower()]
        with open(template_file, "r") as template_code:
            template_content = template_code.read()
        main_content = main_content.replace(PLACE_TO_INSERT_TEMPLATE,
                                            template_content)

    # Guardar main.cpp en el directorio actual
    with open("main.cpp", "w") as main_cpp:
        main_cpp.write(main_content)

    # Copiar CMakeLists_template.txt a CMakeLists.txt
    cmake_template_path = os.path.join(TEMPLATES_DIR, "CMakeLists_template.txt")
    shutil.copyfile(cmake_template_path, "CMakeLists.txt")

    # Crear estructura de directorios de Assets
    assets_dir = "./Assets"
    os.makedirs(os.path.join(
        assets_dir,
        DEFAULT_CONFIG["AUDIO_DIRECTORY"].lstrip("/")), exist_ok=True)
    os.makedirs(os.path.join(
        assets_dir,
        DEFAULT_CONFIG["FONTS_DIRECTORY"].lstrip("/")), exist_ok=True)
    os.makedirs(os.path.join(
        assets_dir,
        DEFAULT_CONFIG["SPRITES_DIRECTORY"].lstrip("/")), exist_ok=True)

    # Generar config.txt
    with open("config.txt", "w") as config_file:
        config_file.write(f"WINDOW_TITLE={window_title}\n")
        config_file.write(f"WIDTH={width}\n")
        config_file.write(f"HEIGHT={height}\n")
        config_file.write(f"FRAMES={frames}\n")
        config_file.write(f"ASSETS_PATH={DEFAULT_CONFIG['ASSETS_PATH']}\n")
        config_file.write(f"AUDIO_DIRECTORY={DEFAULT_CONFIG['AUDIO_DIRECTORY']}\n")
        config_file.write(f"FONTS_DIRECTORY={DEFAULT_CONFIG['FONTS_DIRECTORY']}\n")
        config_file.write(f"SPRITES_DIRECTORY={DEFAULT_CONFIG['SPRITES_DIRECTORY']}\n")
        config_file.write(f"GRAVITY={gravity}\n")
        config_file.write(f"HIT_THRESHOLD={hit_threshold}\n")

    click.echo(f"Project created with {template} template.")


if __name__ == "__main__":
    create_project()
