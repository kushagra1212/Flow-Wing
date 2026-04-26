import React from "react";
import styled, { css } from "styled-components";
import {
  AiOutlineCheckCircle,
  AiOutlineWarning,
  AiOutlineCloseCircle,
} from "react-icons/ai"; // Importing icons
type ToastType = "info" | "warning" | "danger";

// Define a mapping of types to styles for light and dark modes
const typeStyles = {
  info: {
    light: {
      backgroundColor: "#d4edda",
      color: "#155724",
      icon: <AiOutlineCheckCircle />,
    },
    dark: {
      backgroundColor: "#155724",
      color: "#d4edda",
      icon: <AiOutlineCheckCircle />,
    },
  },
  warning: {
    light: {
      backgroundColor: "#fff3cd",
      color: "#856404",
      icon: <AiOutlineWarning />,
    },
    dark: {
      backgroundColor: "#856404",
      color: "#fff3cd",
      icon: <AiOutlineWarning />,
    },
  },
  danger: {
    light: {
      backgroundColor: "#f8d7da",
      color: "#721c24",
      icon: <AiOutlineCloseCircle />,
    },
    dark: {
      backgroundColor: "#721c24",
      color: "#f8d7da",
      icon: <AiOutlineCloseCircle />,
    },
  },
};

// Determine if dark mode is enabled (this is just an example; adjust as needed)
const isDarkMode = true; // This could be derived from props or context

const ToastContainer = styled.div<{ type: ToastType }>`
  position: relative;
  max-width: 100%;
  padding: 16px;
  border-radius: 8px;
  box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
  margin: 10px 0;
  z-index: 1000;
  animation: slideIn 0.5s ease forwards;
  display: flex;
  align-items: flex-start;

  ${({ type }) =>
    css`
      background-color: ${isDarkMode
        ? typeStyles[type].dark.backgroundColor
        : typeStyles[type].light.backgroundColor};
      color: ${isDarkMode
        ? typeStyles[type].dark.color
        : typeStyles[type].light.color};
    `}

  @keyframes slideIn {
    from {
      transform: translateY(-20px);
      opacity: 0;
    }
    to {
      transform: translateY(0);
      opacity: 1;
    }
  }
`;

const ToastTitle = styled.h4`
  margin: 0 0 8px;
  font-size: 18px;
  font-weight: bold;
`;

const ToastMessage = styled.div`
  font-size: 14px;

  p {
    margin: 0;
  }

  a {
    color: #007bff;
    text-decoration: none;

    &:hover {
      text-decoration: underline;
    }
  }

  strong {
    font-weight: bold;
  }

  em {
    font-style: italic;
  }
`;

const ToastIcon = styled.div`
  margin-right: 10px; /* Space between icon and text */
  font-size: 24px; /* Icon size */
`;

const Toast = ({
  title,
  message,
  type,
}: {
  title: string;
  message: string;
  type: ToastType;
}) => {
  return (
    <ToastContainer type={type}>
      <ToastIcon>
        {isDarkMode ? typeStyles[type].dark.icon : typeStyles[type].light.icon}
      </ToastIcon>
      <div>
        <ToastTitle>{title}</ToastTitle>
        <ToastMessage>{message}</ToastMessage>
      </div>
    </ToastContainer>
  );
};

export default Toast;
