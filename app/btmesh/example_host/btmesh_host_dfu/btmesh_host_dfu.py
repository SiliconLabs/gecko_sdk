from app.cli import app_cli
from pathlib import Path

MODULE_FOLDER = Path(__file__).parent.resolve()

if __name__ == "__main__":
    app_cli.main()
