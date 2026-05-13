"""Pytest configuration and shared fixtures."""

from pathlib import Path

import pytest

TESTS_DIR = Path(__file__).parent
HEADERS_DIR = TESTS_DIR / "headers"
REFERENCE_DIR = TESTS_DIR / "reference_output"
