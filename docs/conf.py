# Configuration file for the Sphinx documentation builder.

# -- Project information -----------------------------------------------------
project = "ttt"
copyright = "2022, ttt"
author = "ttt"

# -- General configuration ---------------------------------------------------
extensions = ["breathe"]
templates_path = ["_templates"]
exclude_patterns = ["_build", "Thumbs.db", ".DS_Store"]

# -- Options for HTML output -------------------------------------------------
html_theme = "sphinx_rtd_theme"
html_static_path = ["_static"]
html_css_files = ["main_stylesheet.css"]

# -- Breathe Configuration ---------------------------------------------------
breathe_default_project = "ttt"
