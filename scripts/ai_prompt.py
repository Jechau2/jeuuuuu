#!/usr/bin/env python3
"""Query TinyLlama model using llama-cpp-python."""

import sys
from pathlib import Path

MODEL_PATH = Path(__file__).resolve().parent.parent / "models" / "TinyLlama.Q4_0.gguf"


def main() -> int:
    prompt = " ".join(sys.argv[1:]) if len(sys.argv) > 1 else sys.stdin.read()
    try:
        from llama_cpp import Llama
    except Exception as exc:
        sys.stderr.write(f"Failed to import llama_cpp: {exc}\n")
        return 1

    try:
        llm = Llama(model_path=str(MODEL_PATH), n_ctx=512)
        output = llm(prompt, max_tokens=128)
        print(output["choices"][0]["text"].strip())
    except Exception as exc:
        sys.stderr.write(f"LLM error: {exc}\n")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
